package io.muoncore.discovery.multicast.impl;

import io.muoncore.discovery.DiscoveryJni;
import io.muoncore.discovery.multicast.ServiceDescriptor;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.MulticastSocket;
import java.util.Random;

public class ServiceDescriptorServer
{
    DiscoveryJni.ServiceDescriptorServer serviceDescriptorServer;
    public static final String MULTICAST_ADDRESS = "224.1.7.8";
    public static final int PORT = 9898;
    public static final int MAX_TRANSMIT_INTERVAL = 5000;
    public static final GsonCodec CODEC = new GsonCodec();
    private Thread thread;
    private boolean enabled;
    private ServiceDescriptor serviceDescriptor;

    public void setServiceDescriptor( ServiceDescriptor serviceDescriptor )
    {
        this.serviceDescriptor = serviceDescriptor;
    }

    public void setEnabled( boolean enabled )
    {
        this.enabled = enabled;
        if( enabled && thread == null || !thread.isAlive() ){
            thread = new Thread( this::run, this.getClass().getSimpleName() );
            thread.setDaemon(true);
            thread.start();
        }
    }

    private void run()
    {
        try( MulticastSocket socket = new MulticastSocket(4445) ){
            while( enabled ){
                byte[] buf = CODEC.encode(serviceDescriptor);
                DatagramPacket packet = new DatagramPacket( buf, buf.length, InetAddress.getByName(MULTICAST_ADDRESS), PORT );
                if( socket.isBound() ){
                    socket.send(packet);
                }
                try{
                    Thread.sleep( new Random().nextInt(MAX_TRANSMIT_INTERVAL) );
                }
                catch( InterruptedException e ){
                    e.printStackTrace();
                }
            }
        }
        catch( IOException e ){
            e.printStackTrace();
        }
    }
}