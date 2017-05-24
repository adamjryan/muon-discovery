package io.muoncore.discovery.multicast;

import io.muoncore.discovery.DiscoveryJni;
import io.muoncore.discovery.DiscoveryJni.ServiceDescriptorPointerVector;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class MulticastDiscovery implements Discovery
{
    private final DiscoveryJni.MulticastDiscovery multicastDiscovery = new DiscoveryJni.MulticastDiscovery();
    private final ServiceDescriptorPointerVector serviceDescriptorPointerVector = new ServiceDescriptorPointerVector();
    private Map<DiscoveryJni.ServiceDescriptor,ServiceDescriptor> jniServiceDescriptorMap = new HashMap<>();

    public void setEnabled( boolean enabled )
    {
        multicastDiscovery.setEnabled(enabled);
    }

    @Override
    public void onReady( DiscoveryOnReady onReady )
    {
        onReady.call();
    }

    @Override
    public void advertiseLocalService( ServiceDescriptor serviceDescriptor )
    {
        multicastDiscovery.advertiseLocalService( serviceDescriptor.asJni() );
    }

    @Override
    public List<ServiceDescriptor> getKnownServices()
    {
        serviceDescriptorPointerVector.resize(0);
        multicastDiscovery.getKnownServices(serviceDescriptorPointerVector);
        long size = serviceDescriptorPointerVector.size();
        if( size < 1 ){
            return Collections.emptyList();
        }
        Map<DiscoveryJni.ServiceDescriptor,ServiceDescriptor> newServiceDescriptors = new HashMap<>();
        int index = 0;
        while( index < size ){
            DiscoveryJni.ServiceDescriptor jniServiceDescriptor = serviceDescriptorPointerVector.get(index++);
            ServiceDescriptor serviceDescriptor = jniServiceDescriptorMap.get(jniServiceDescriptor);
            if( serviceDescriptor == null ){
                serviceDescriptor = new ServiceDescriptor(jniServiceDescriptor);
            }
            newServiceDescriptors.put( jniServiceDescriptor, serviceDescriptor );
        }
        jniServiceDescriptorMap = newServiceDescriptors;
        return new ArrayList<>( jniServiceDescriptorMap.values() );
    }
}