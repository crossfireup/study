#!/usr/bin/env ruby

require 'net/http'

h = Net::HTTP.new('10.0.128.32', 80)
response = h.get('/', nil)
if response.message == 'OK'
	puts response.body.scan(/<img src="(.*?)"/m).uniq
end

require 'open-uri'
open('http://10.0.128.32') do |f|
	puts f.read.scan(/<img src="(.*?)"/m).uniq
end
