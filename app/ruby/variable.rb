#!/usr/bin/env ruby

A = 4

puts A, A.object_id

def modify(param)
    param = "b"
    puts param.object_id
end

A = modify(A)
puts A



class T
    TA = "4"
    class V
        TA = "6"
        puts TA
    end
end

t = T::V.new

puts T::TA, T::V::TA