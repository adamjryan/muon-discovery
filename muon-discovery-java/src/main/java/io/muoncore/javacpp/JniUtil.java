package io.muoncore.javacpp;

import io.muoncore.discovery.DiscoveryJni.StringVector;
import io.muoncore.discovery.DiscoveryJni.URI;
import io.muoncore.discovery.DiscoveryJni.URIVector;

/**
 * Created by adam on 17/05/17.
 */
public class JniUtil
{
    public static void addAllTo( Iterable<URI> source, URIVector destination )
    {
        for( URI sourceItem : source ){
            destination.put(sourceItem);
        }
    }

    public static void addAllTo( Iterable<String> source, StringVector destination )
    {
        for( String sourceItem : source ){
            destination.put(sourceItem);
        }
    }
}