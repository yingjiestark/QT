#!/bin/bash
build_dir=$1
if [ -z "$build_dir" ] ;then
	echo "error!请输入build目录，如果没有编译请先编译。"
	echo "例如：$0 /home/uos/Desktop/build-tools-unknown-Debug"
	exit 0
fi
cd $build_dir
lcov -d ./ -c -o init.info 
lcov -a init.info -o total.info
lcov --remove total.info '*/usr/include/*' '*/usr/lib/*' '*/usr/lib64/*' '*/src/log/*' '*/tests/*' '*/usr/local/include/*' '*/usr/local/lib/*' '*/usr/local/lib64/*' '*/third/*' 'testa.cpp' -o final.info
genhtml -o cover_report --legend --title "lcov"  --prefix=./ final.info
uos-browser-stable cover_report/index.html &