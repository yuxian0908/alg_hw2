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
1. (done) Spolygon裡的Epolygon製造方式目前有誤，應該要先找出head之後再開始接，現在這樣只是找隨便一個而已
2. (done) Epolygon clip, merge
3. 萬一操作剛好是在firstNode的情形
4. containNode裡面水平最遠的那個點要思考一下如何處理
5. Spolygon merge, clip裡的epolygon操作記得加上去
6. 共線問題
7. merge卻完全沒有重疊問題
