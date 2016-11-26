#!/usr/bin/env ruby

require 'net/http'

pages = %w( www.rubycental.com slashdot.com www.bing.com www.baidu.com )
threads = []
for cur_page in pages
	threads << Thread.new(cur_page) do |url|
		h = Net::HTTP.new(url, 80)
		puts "Fetching #{url}"
		resp = h.get('/', nil)
		puts "Got #{url}: #{resp.message}"
	end
end
threads.each { |t| t.join}

threads = []
count = 0
10.times do |i|
	threads << Thread.new do 
		sleep(rand(0.1))
		Thread.current["mycount"] = count
		count += 1
	end
end
threads.each { |t| t.join; puts t["mycount"]}
puts "count = #{count}"
