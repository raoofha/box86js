
sed -e '/_BOX86JS_/r box86.js' -e '/_BOX86JS_/d' $1/src/browser/box86.html > box86.html &&
htmlSize=$(printf '%14d' `cat box86.html | wc -c`) &&
wasmSize=$(printf '%14d' `cat box86.wasm | wc -c`) &&
sed -i -e "s/_14W_HTMLSIZE_/$htmlSize/g"  -e "s/_14W_WASMSIZE_/$wasmSize/g" box86.html &&
cat box86.wasm >> box86.html &&
box86Size=`cat box86.html | wc -c`
if [ $(($htmlSize + $wasmSize)) -ne $box86Size ] ; then
  echo $htmlSize + $wasmSize != $box86Size
  exit -1
fi
echo $htmlSize + $wasmSize = $(($htmlSize + $wasmSize)) == $box86Size

~/playground/bin/addDataToElfFile box86.html ~/playground/bin/tetris tetris.html &&
~/playground/bin/addDataToElfFile box86.html ~/playground/bin/2048   2048.html &&
~/playground/bin/addDataToElfFile box86.html ~/playground/bin/2048-i386.AppImage 2048-i386.AppImage.html
