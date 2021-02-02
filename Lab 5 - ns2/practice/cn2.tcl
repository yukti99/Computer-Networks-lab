#Create a simulator object
set ns [new Simulator]

#Define different colors for data flows (for NAM)
$ns color 1 Purple
$ns color 2 Blue

#Open the NAM trace file
set nf [open out.nam w]
$ns namtrace-all $nf

#Define a 'finish' procedure
proc finish {} {
        global ns nf
        $ns flush-trace
        #Close the NAM trace file
        close $nf
        #Execute NAM on the trace file
        exec nam out.nam &
        exit 0
}

#Create two nodes
set source1 [$ns node]
set dest1 [$ns node]

#Create duplex link between the nodes
$ns duplex-link $source1 $dest1 2Mb 100ms DropTail

#Set Queue Size of link (source1-dest1) to 10
$ns queue-limit $source1 $dest1 10

#Give node position (for NAM)
$ns duplex-link-op $source1 $dest1 orient right

#Monitor the queue for link  (source1-dest1). (for NAM)
$ns duplex-link-op $source1 $dest1 queuePos 0.5
$ns duplex-link-op $dest1 $source1 queuePos 0.5


#Setup a TCP connection
set tcp [new Agent/TCP]
$tcp set class_ 2
$ns attach-agent $source1 $tcp
set sink [new Agent/TCPSink]
$ns attach-agent $dest1 $sink
$ns connect $tcp $sink
$tcp set fid_ 1

#Setup a FTP over TCP connection
set ftp [new Application/FTP]
$ftp attach-agent $tcp
$ftp set type_ FTP

#Setup a UDP connection
set udp [new Agent/UDP]
$ns attach-agent $dest1 $udp
set null [new Agent/Null]
$ns attach-agent $source1 $null
$ns connect $udp $null
$udp set fid_ 2

#Setup a CBR over UDP connection
set cbr [new Application/Traffic/CBR]
$cbr attach-agent $udp
$cbr set type_ CBR
$cbr set packet_size_ 1000
$cbr set rate_ 1mb
$cbr set random_ false


#Schedule events for the FTP agent
$ns at 0.1 "$cbr start"
$ns at 0.5 "$ftp start"
$ns at 4.0 "$ftp stop"
$ns at 4.5 "$cbr stop"

# to print label on top of src and dest
$ns at 0.0 "$source1 label Source"
$ns at 0.0 "$dest1 label Destination"

#Call the finish procedure after 5 seconds of simulation time
$ns at 5.0 "finish"

#Run the simulation
$ns run
