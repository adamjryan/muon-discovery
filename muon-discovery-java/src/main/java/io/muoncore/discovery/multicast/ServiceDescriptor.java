package io.muoncore.discovery.multicast;

import io.muoncore.discovery.DiscoveryJni;
import io.muoncore.javacpp.JniStringList;
import io.muoncore.javacpp.JniUriList;
import io.muoncore.javacpp.JniUtil;

import java.util.Collection;
import java.util.List;

public class ServiceDescriptor
{
    private final DiscoveryJni.ServiceDescriptor serviceDescriptor;

    public ServiceDescriptor( DiscoveryJni.ServiceDescriptor serviceDescriptor )
    {
        this.serviceDescriptor = serviceDescriptor;
    }

    public ServiceDescriptor( String identifier, List<String> tags, List<String> codecs, List<DiscoveryJni.URI> connectionUrls, Collection<String> capabilities )
    {
        assert identifier != null;
        serviceDescriptor = new DiscoveryJni.ServiceDescriptor( identifier );
        JniUtil.addAllTo( tags, serviceDescriptor.getTags() );
        JniUtil.addAllTo( codecs, serviceDescriptor.getCodecs() );
        JniUtil.addAllTo( connectionUrls, serviceDescriptor.getConnectionUris() );
        JniUtil.addAllTo( capabilities, serviceDescriptor.getCapabilities() );
    }

    @Override
    public boolean equals( Object object )
    {
        return this == object || !( object == null || getClass() != object.getClass() ) && getIdentifier().equals( ((ServiceDescriptor)object).getIdentifier() );
    }

    @Override
    public int hashCode()
    {
        return getIdentifier().hashCode();
    }

    public String[] getCodecs()
    {
        return new JniStringList( serviceDescriptor.getCodecs() ).toArray( new String[0] );
    }

    public List<String> getTags()
    {
        return new JniStringList( serviceDescriptor.getTags() );
    }

    public String getIdentifier()
    {
        return serviceDescriptor.getIdentifier().getString();
    }

    public List<DiscoveryJni.URI> getConnectionUrls()
    {
        return new JniUriList( serviceDescriptor.getConnectionUris() );
    }

    public Collection<String> getCapabilities()
    {
        return new JniStringList( serviceDescriptor.getCapabilities() );
    }

    public DiscoveryJni.ServiceDescriptor asJni()
    {
        return serviceDescriptor;
    }
}
