set ns [new Simulator] 

$ns color 1 Purple

# nam trace file
set nf [open A51.nam w] 
$ns namtrace-all $nf 
set nr [open A51.tr w]
$ns trace-all $nr



# finish procedure
proc finish {} { 
	global ns nf 
	$ns flush-trace
	close $nf	
	exec nam out.nam & 
	exit 0
} 

set n0 [$ns node] 
set n1 [$ns node] 
set n2 [$ns node]


# creating duplex links between nodes
$ns duplex-link $n0 $n1 1.5Mb 10ms DropTail 
$ns duplex-link $n1 $n2 512Kb 10ms DropTail 


# setting queue limit
$ns queue-limit $n1 $n2 5


#creating a udp connection in network simulator
set udp0 [new Agent/UDP]
$ns attach-agent $n0 $udp0

#set up CBR over udp
set cbr0 [new Application/Traffic/CBR]
$cbr0 set packetSize_ 500
$cbr0 set interval_ 0.005
$cbr0 attach-agent $udp0

set sink [new Agent/Null]
$ns attach-agent $n2 $sink
$ns connect $udp0 $sink

# time of start and end the cbr traffic
$ns at 0.1 "$cbr0 start"
$ns at 4.0 "$cbr0 stop"


# time to finish
$ns at 4.5 "finish"

# run ns2
$ns run 






