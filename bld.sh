#!/bin/bash

bld(){
	g++ $1 -o a.out `pkg-config --cflags --libs opencv`
}

bld $1