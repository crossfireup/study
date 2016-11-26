puts 'hello word'

puts %q!hllockjskdfj /t /b /s //!

puts "a","b","c"

print "a","b","c","\n"

puts <<EOF
hello c world
how are you ?
I am fine and you ?
I'm ok !
EOF

a="helloc"
puts a
b=a
puts b
c=b 
puts c
b="blue"
puts a,b,c




a = gets.chomp.to_i
unless a > 5
	puts "#{a} < 5"
else
	puts "#{a} > = 5"
end
if a < 5
	puts "#{a} < 5"
elsif a > 7
	puts "#{a} > 7"
else
	puts "cheese sandwich!"
end




h = { "a" => "hello a", "b" => "hello b"}
puts "helloc".class
puts 1.class
puts nil.class
puts h.class
puts :symbol.class



hash = {:a => "a sysmbol", :b => "b sysmbol", :c => "c symbo", :b => "new b smbol"}

puts hash[:a]
puts hash[:b]
puts hash[:c]

hash = {:a => "a sysmbol", :b => "b sysmbol", :c => "c symbo", :b => "new b smbo
l", "d" => "d", "e" => "e", "d" => "new d" }
hash.each do | key, value|
	print key,":",value,"\n"
end
