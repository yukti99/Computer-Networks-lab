BEGIN{ 
	dropped=0;
	sent=0;
	recieved=0;
	pkt=0;
	time=0;
	
}
{
	if($1=="d"){
		dropped++;
	}
	if($1=="r"){
		recieved++;
		pkt = pkt+$6;
		time=$2;
	}
	if($1=="s"){
		sent++;
	}
	
}
END{ 
	printf("No of packets dropped = %d\n",dropped);
	printf("No of packets recieved = %d\n",recieved);
	sent=dropped+recieved;
	printf("No of packets sent = %d\n",sent);
	printf("Packet delivery ratio = %.6f\n",recieved*100/sent);
	printf("Throughput = %.6fMbps\n",((pkt/time)*(8/1000000)));
}
