#!/usr/bin/env ruby

def do_twice
	yield
	yield
end

do_twice { puts "hola"}


def fun_do_twice(f)
	f.call
	f.call
end

fun_do_twice lambda { puts "fun hola"}
