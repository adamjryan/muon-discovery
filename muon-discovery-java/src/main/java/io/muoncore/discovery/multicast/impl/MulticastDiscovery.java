package io.muoncore.discovery.multicast.impl;

import io.muoncore.discovery.multicast.Discovery;
import io.muoncore.discovery.multicast.ServiceDescriptor;

import java.util.List;

public class MulticastDiscovery implements Discovery
{
    private final ServiceDescriptorServer serviceDescriptorServer = new ServiceDescriptorServer();
    private final ServiceDescriptorClient serviceDescriptorClient = new ServiceDescriptorClient();

    public MulticastDiscovery()
    {
        serviceDescriptorServer.setEnabled(true);
        serviceDescriptorClient.setEnabled(true);
    }

    public void setEnabled( boolean enabled )
    {
        serviceDescriptorServer.setEnabled(enabled);
        serviceDescriptorClient.setEnabled(enabled);
    }

    @Override
    public void onReady( DiscoveryOnReady onReady )
    {
        onReady.call();
    }

    @Override
    public void advertiseLocalService( ServiceDescriptor serviceDescriptor )
    {
        serviceDescriptorServer.setServiceDescriptor(serviceDescriptor);
    }

    @Override
    public List<ServiceDescriptor> getKnownServices()
    {
        return serviceDescriptorClient.getServiceCache().getServices();
    }
}