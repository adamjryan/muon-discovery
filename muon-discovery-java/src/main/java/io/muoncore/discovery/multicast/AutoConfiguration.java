package io.muoncore.discovery.multicast;

import java.util.ArrayList;
import java.util.List;
import java.util.Properties;

public class AutoConfiguration
{
    private String serviceName;
    private List<String> tags = new ArrayList<>();
    private Properties config = new Properties();

    public void setTags( List<String> tags )
    {
        this.tags = tags;
    }

    public List<String> getTags()
    {
        return tags;
    }

    public void setServiceName( String serviceName )
    {
        this.serviceName = serviceName;
    }

    public String getServiceName()
    {
        return serviceName;
    }

    public Properties getProperties()
    {
        return config;
    }

    public boolean getBooleanConfig( String name )
    {
        return Boolean.parseBoolean( config.getProperty(name) );
    }

    public long getLongConfig( String name )
    {
        return Long.parseLong( config.getProperty(name) );
    }

    public long getLongConfig( String name, long defaultValue )
    {
        try{
            return Long.parseLong( config.getProperty(name) );
        }
        catch( NumberFormatException ex ){
            return defaultValue;
        }
    }

    public String getStringConfig( String name )
    {
        return config.getProperty(name);
    }
}