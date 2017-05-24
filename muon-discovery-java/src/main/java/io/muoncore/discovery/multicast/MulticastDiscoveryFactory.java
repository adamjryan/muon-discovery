package io.muoncore.discovery.multicast;

import java.util.Properties;

public class MulticastDiscoveryFactory implements DiscoveryFactory
{
    @Override
    public Discovery build( Properties properties )
    {
        return new MulticastDiscovery();
    }

    @Override
    public void setAutoConfiguration( AutoConfiguration autoConfiguration )
    {
    }
}