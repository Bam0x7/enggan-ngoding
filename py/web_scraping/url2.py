import urllib3

# Making the request (The request function returns HTTPResponse object)
http = urllib3.PoolManager()
resp = http.request("GET", "https://httpbin.org/ip")

print(resp.status)
# 200
print(resp.data)
# b"{\n  "origin": "104.232.115.37"\n}\n"
print(resp.headers)
# HTTPHeaderDict({"Content-Length": "32", ...})