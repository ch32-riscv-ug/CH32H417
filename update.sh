#!/bin/bash

cd `dirname $0`

git pull

# https://www.wch-ic.com/products/CH32H417.html
cd datasheet_en
# https://www.wch-ic.com/downloads/CH32H417DS0_PDF.html
curl -z CH32H417DS0.PDF -o CH32H417DS0.PDF https://www.wch-ic.com/download/file?id=423
cd ..

# https://www.wch.cn/products/CH32H417.html
cd datasheet_zh
# https://www.wch.cn/downloads/CH32H417DS0_PDF.html
curl -z CH32H417DS0.PDF -o CH32H417DS0.PDF https://www.wch.cn/download/file?id=529
# https://www.wch.cn/downloads/CH32H417RM_PDF.html
#curl -z CH32H417RM.PDF -o CH32H417RM.PDF https://www.wch.cn/download/file?id=532
cd ..

# https://www.wch.cn/downloads/CH32H417EVT_ZIP.html
curl -z CH32H417EVT.ZIP -o CH32H417EVT.ZIP https://www.wch.cn/download/file?id=530
rm -rfv EVT
unzip -O GB2312 *.ZIP

git add . --all
git commit -m "update"
git push origin main
