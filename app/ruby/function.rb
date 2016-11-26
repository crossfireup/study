#!/usr/bin/env ruby


def accept_hash(var)
	print "got: ",var.inspect
end

accept_hash( 2=>"2", 3 =>3, 4=>4, 5 => "5", 6 =>6){ |s| puts s}
