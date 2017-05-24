package io.muoncore.test.discovery;

import io.muoncore.discovery.DiscoveryJni.URI;
import io.muoncore.discovery.multicast.AutoConfiguration;
import io.muoncore.discovery.multicast.Discovery;
import io.muoncore.discovery.multicast.MulticastDiscoveryFactory;
import io.muoncore.discovery.multicast.ServiceDescriptor;
import org.junit.Test;

import java.util.ArrayList;
import java.util.List;
import java.util.Properties;

/**
 * Created by adam on 07/05/17.
 */
public class TestMulticastDiscovery
{
    @Test
    public void testBroadcastReceive()
    {
        MulticastDiscoveryFactory multicastDiscoveryFactory = new MulticastDiscoveryFactory();
        multicastDiscoveryFactory.setAutoConfiguration( new AutoConfiguration() );
        Discovery discoveryBroadcaster = multicastDiscoveryFactory.build( new Properties() );

        List<String> tags = new ArrayList<>();
        tags.add("brand-new");
        List<String> codecs = new ArrayList<>();
        codecs.add("encoding-1");
        List<URI> connectionUris = new ArrayList<>();
        connectionUris.add( new URI() );
        List<String> capabilities = new ArrayList<>();
        capabilities.add("ping");
        discoveryBroadcaster.advertiseLocalService( new ServiceDescriptor( "test-service", tags, codecs, connectionUris, capabilities ) );
        try{
            Thread.sleep(500);
        }
        catch( InterruptedException e ){
            e.printStackTrace();
        }
        Discovery discoveryListener = multicastDiscoveryFactory.build( new Properties() );
        List<ServiceDescriptor> serviceDescriptors = discoveryListener.getKnownServices();
        while( serviceDescriptors.size() < 1 ){
            System.out.println("Polling for services.");
            try{
                Thread.sleep(1000);
            }
            catch( InterruptedException e ){
                e.printStackTrace();
            }
            serviceDescriptors = discoveryListener.getKnownServices();
        }
        System.out.print("Service found: ");
        ServiceDescriptor serviceDescriptor = serviceDescriptors.get(0);
        String identifier = serviceDescriptor.getIdentifier();
        System.out.println(identifier);
    }
}