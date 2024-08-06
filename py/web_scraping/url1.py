import urllib3

http = urllib3.PoolManager()
resp = http.request(
    "POST",
    "https://httpbin.org/post",
    fields={"hello":"worlds"}
)

print(resp.data)