package io.muoncore.discovery.multicast;


import java.util.Properties;

public interface DiscoveryFactory
{
    Discovery build( Properties properties );
    void setAutoConfiguration( AutoConfiguration autoConfiguration );
}