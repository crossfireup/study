#!/usr/bin/env ruby


def run(id)
    print 'now id'
end


t = Thread.new{ puts 'helloc'; run(1)}
