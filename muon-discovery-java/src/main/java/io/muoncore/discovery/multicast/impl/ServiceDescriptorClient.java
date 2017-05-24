package io.muoncore.discovery.multicast.impl;

import io.muoncore.discovery.multicast.ServiceDescriptor;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.MulticastSocket;
import java.util.AbstractMap.SimpleEntry;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import java.util.stream.Collectors;

public class ServiceDescriptorClient
{
    public static class ServiceCache
    {
        private Map<String,Entry<ServiceDescriptor,Long>> serviceCache = new HashMap<>();

        private ServiceCache(){}

        public List<ServiceDescriptor> getServices()
        {
            Map<String,Entry<ServiceDescriptor,Long>> entries = new HashMap<>();
            for( Entry<String,Entry<ServiceDescriptor,Long>> entry : serviceCache.entrySet() ){
                Entry<ServiceDescriptor,Long> entryValue = entry.getValue();
                long val = entryValue.getValue() + ServiceDescriptorServer.MAX_TRANSMIT_INTERVAL - System.currentTimeMillis();
                if( val > 0 ){
                    entries.put( entry.getKey(), entryValue );
                }
            }
            serviceCache = entries;
            return serviceCache.values().stream().map(Entry::getKey).collect( Collectors.toList() );
        }

        private void addService( ServiceDescriptor service )
        {
            serviceCache.put(  service.getIdentifier(), new SimpleEntry<>( service, System.currentTimeMillis() )  );
        }
    }

    private final ServiceCache serviceCache = new ServiceCache();
    private Thread thread;
    private boolean enabled;

    public void setEnabled( boolean enabled )
    {
        this.enabled = enabled;
        if( enabled && thread == null || !thread.isAlive() ){
            thread = new Thread( this::run, this.getClass().getSimpleName() );
            thread.setDaemon(true);
            thread.start();
        }
    }

    public ServiceCache getServiceCache()
    {
        return serviceCache;
    }

    private void run()
    {
        try( MulticastSocket socket = new MulticastSocket(ServiceDescriptorServer.PORT) ){
            socket.setReuseAddress(true);
            socket.setLoopbackMode(true);
            InetAddress address = InetAddress.getByName(ServiceDescriptorServer.MULTICAST_ADDRESS);
            socket.joinGroup( address );
            DatagramPacket packet;
            while( enabled ){
                byte[] buf = new byte[512];
                packet = new DatagramPacket( buf, buf.length );
                socket.receive( packet );
                byte[] data = Arrays.copyOfRange( buf, 0, packet.getLength() );
                ServiceDescriptor descriptor = ServiceDescriptorServer.CODEC.decode( data, ServiceDescriptor.class );
                System.out.println( "Got data " + descriptor.getIdentifier() );
                serviceCache.addService(descriptor);
            }
            socket.leaveGroup(address);
            socket.close();
        }
        catch( IOException e ){
            e.printStackTrace();
        }
    }
}