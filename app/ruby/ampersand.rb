#!/usr/bin/env ruby


def contrived(a, &f)
	f.call(a)
	yield(a)
end


res = contrived(25) { |x| puts x}
puts res.class

# contrived(25, lambda { |x| puts x})
