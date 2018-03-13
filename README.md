### 说明

暂时只支持get请求, 不支持Transfer-Encoding: chunked, 只支持Content-Length: xxx

### 使用方式

### 下载

```
git clone git@github.com:weiwenwang/mini-bench.git
```

### 编译

```
cd mini-bench/build
cmake ..
make
```

### 执行

```apple js
./mini-bench -t 100 -p 200 -u http://www.baidu.com/index.php --type=get
```
