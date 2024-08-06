import urllib3
import certifi

http = urllib3.PoolManager(ca_certs=certifi.where())
url = 'https://httpbin.org/get'
payload = {'name': 'bam', 'age': 24}
resp = http.request('GET',url, fields=payload)

print(resp.data.decode('UTF-8'))
