#!/usr/bin/env ruby

require 'net/imap'

imap = Net::IMAP.new('imap.163.com', 993, true, nil, false)
imap.login('kunis2008@163.com', '')
begin
    imap.select('INBOX')
    imap.search(["RECENT"]).each do |message_id|
        envolope = imap.fetch(message_id, "ENVELOPE")[0].attr["ENVELOPE"]
        puts "#{envelope.from[0].name}: \t #{envelope.subject}"
    end
ensure
    imap.logout()
    imap.disconnect()
    print "logout and disconnect from server!\n"
end
