import urllib3

http = urllib3.PoolManager()
resp = http.request("GET","https://httpbin.org/robots.txt")

print(resp.data)