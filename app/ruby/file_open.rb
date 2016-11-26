#!/usr/bin/env ruby

class File
	def File.open(*args)
		result = f = File.new(*args)
		if block_given?
			puts "given block"
			begin
				result = yield(f)
			ensure
				puts "file close"
				f.close
			end
		end
		return result
	end
end

File.open("call_module.rb", "r") do |f|
	f.each do |line|
		puts line
	end
end
File.open("call_module.rb", 'r') { a() }
