.PHONY: libvector
vector:
	rm -f buid/lib$@
	go build -o build/lib$@ pkg/$@/$@.go

.PHONY: lab3
lab3:
	rm -rf build/$@
	go build -o build/$@ cmd/$@.go

