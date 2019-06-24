## run code
```
1. make all
2. ./main.exe
```

## structure
1. DS:
```
1. 實心：逆時針 linked list
2. 空心：順時針 linked list
```

2. merge:
```
1. 實心：刪除互相in，加交界點
2. 空心：刪除空in實，加交界點
```

3. clip:
```
1. 實心：刪除實in空，加交界點
2. 空心：當成實心merge
```

4. split:
```
連續兩點連線split
```

## Test on Linux
```
1. scp -P 40051 -r ./tmp alu1847@edaunion.ee.ntu.edu.tw:./
2. ssh alu1847@edaunion.ee.ntu.edu.tw -p 40051
3. EeHijav2
```


## TODO
1. firstNode->printNode 改成 printPolygon
2. 要split之前先呼叫storeInPool
