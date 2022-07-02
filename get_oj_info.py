import html
import json
from math import ceil
import os
import re
import requests


def getFiles(path:str = os.getcwd()):
    for root, dirs, files in os.walk(path):
        return dirs, files

def removeEndingLines(s:str) -> str:
    return re.sub(r'\n*$', '', s)

def parseDesp(s:str) -> str:
    def getMatched(matched) -> str:
        return matched.group('content')
    def parsePara(matched) -> str:
        return f'{getMatched(matched)}\n'
    def parseStrong(matched) -> str:
        return f'**{getMatched(matched)}**'
    def parseList(matched) -> str:
        def getMatchedList(matched) -> str:
            return f'- {getMatched(matched)}\n'
        return re.sub(r'<li>(?P<content>.*?)</li>', getMatchedList, matched.group('content'))
    def parseCode(matched) -> str:
        return f'\'\'\'\n{getMatched(matched)}\n\'\'\'\n'
    s = re.sub(r'<p(.*?)>(?P<content>.*?)</p>', parsePara, s)
    s = re.sub(r'<br ?/?>', '\n', s)
    s = re.sub(r'<span(.*?)>(?P<content>.*?)</span>', getMatched, s)
    s = re.sub(r'<strong>(?P<content>.*?)</strong>', parseStrong, s)
    s = re.sub(r'<b(.*?)>(?P<content>.*?)</b>', parseStrong, s)
    s = re.sub(r'<a(.*?)>(?P<content>.*?)</a>', parseStrong, s)
    s = re.sub(r'<img(.*?)>', '\n*image deleted*\n', s)
    s = re.sub(r'<ul>(?P<content>.*?)</ul>', parseList, s)
    s = re.sub(r'<pre><code>(?P<content>.*?)</code></pre>', parseCode, s, flags= re.M | re.S)
    # escape "/**/"
    s = re.sub(r'/\*', r'\\/\\\*', s)
    s = re.sub(r'\*/', r'\\\*\\/', s)
    # remove '\n's in tail
    s = removeEndingLines(s)
    # unescape html entity
    s = html.unescape(s)
    return s

def getID(title:str) -> str:
    def getMatched(matched) -> str:
        return matched.group('matched')
    return re.sub(r'(?P<matched>(\d+)(\.\d+)?)(.*)', getMatched, title)

def parseSamples(l:list) -> str:
    s = '\n'.join([f'''## 样例{i+1}
### 输入
{removeEndingLines(l[i]['input'])}

### 输出
{removeEndingLines(l[i]['output'])}
''' for i in range(len(l))])
    # escape "/**/"
    s = re.sub(r'/\*', r'\\/\\\*', s)
    s = re.sub(r'\*/', r'\\\*\\/', s)
    return s



with open('conf.json', 'r') as f:
    conf = json.load(f)

# get oj info from api
req = requests.get(f"{conf['oj']}/api/problem?limit=20")
req = json.loads(req.content)
total:int = req['data']['total']
result:list = req['data']['results']
for i in range(1, ceil(total/20)):
    req = requests.get(f"{conf['oj']}/api/problem?limit=20&offset={i*20}")
    result.extend(json.loads(req.content)['data']['results'])

print(f'total: {result.__len__()}')

# pre-process data
data = {
    getID(item['title']) : {
        'title': item['title'],
        'description': parseDesp(item['description']),
        'input_description': parseDesp(item['input_description']),
        'output_description': parseDesp(item['output_description']),
        'samples': parseSamples(item['samples'])
    } for item in result
}


# with open('data.json', 'w') as f:
#     json.dump(data, f, indent=2, ensure_ascii=False)

OJ_PATH = os.path.join(os.getcwd())

dirs, _ = getFiles(OJ_PATH)
for d in dirs:
    if d == 'groupwork':
        continue
    d = os.path.join(OJ_PATH, d)
    _, files = getFiles(d)
    for filename in files:
        if not filename.endswith('.c'):
            continue
        info = data[getID(filename)]
        filename = os.path.join(OJ_PATH, d, filename)

        with open(filename, 'r') as f:
            content = f.read()

        if content.startswith('/*'):
            continue

        with open(filename, 'w') as f:
            f.write(f'''/*
# {info['title']}
## 描述
{info['description']}

## 输入
{info['input_description']}

## 输出
{info['output_description']}

{info['samples']}
*/

{content}''')

