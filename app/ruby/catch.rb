#!/usr/bin/env ruby


def promtAndGet(prompt)
	print prompt
	str = gets.chomp
	throw :quitRequested if str == "!"
	return str
end

catch :quitRequested do
	name = promtAndGet("name:")
	age = promtAndGet("age:")
	sex = promtAndGet("sex:")
	puts name,age,sex
end

