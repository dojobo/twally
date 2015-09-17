require 'twitter'
require 'rubyserial'
require 'psych'

credentials = Psych.load_file('credentials.yml') 
device = ARGV[0]
tracking_terms = ARGV[1..-1]
term_list = tracking_terms.join(",")
tweet_count = 0

client = Twitter::Streaming::Client.new do |config|
  config.consumer_key = credentials['consumer_key']
  config.consumer_secret = credentials['consumer_secret']
  config.access_token = credentials['access_token']
  config.access_token_secret = credentials['access_token_secret']
end

serial_port = Serial.new device, 9600

Thread.new do 
  while true do 
    serial_port.write(tweet_count)
    sleep 0.5
  end
end

puts "Listening for #{term_list}..."
client.filter(track: term_list) do |object|
  if object.is_a?(Twitter::Tweet) then 
    tweet_count += 1
    puts "#{tweet_count}: #{object.text}"
  end
end