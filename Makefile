SERVICE_NAME=gfb-cam-snapshot
VERSION=1.0.0
EMAIL=go.for.broke1006@gmail.com
BUILD_DIR=./build/

all:
	echo 'Hello'

clean-dist:
	rm -rf cmake-build-debug || true
	rm -rf debian || true
	rm -rf obj-*-linux-gnu || true
