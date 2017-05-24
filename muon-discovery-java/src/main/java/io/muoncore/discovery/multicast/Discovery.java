package io.muoncore.discovery.multicast;

import java.net.URI;
import java.util.List;
import java.util.Optional;
import java.util.concurrent.CountDownLatch;
import java.util.function.Predicate;

public interface Discovery
{
    interface DiscoveryOnReady
    {
        void call();
    }

    void setEnabled( boolean enabled );

    default void blockUntilReady()
    {
        CountDownLatch latch = new CountDownLatch(1);
        onReady( latch::countDown );
        synchronized(this){
            try{
                latch.await();
            }
            catch( InterruptedException e ){
                e.printStackTrace();
            }
        }
    }

    void onReady( DiscoveryOnReady onReady );

    /**
     * Advertise a particular service.
     * If null, then nothing is advertised by the local process
     *
     * @param descriptor
     */
    void advertiseLocalService( ServiceDescriptor descriptor );

    /**
     * Return all of the services that are currently visible by this discovery mechanism
     *
     * @return
     */
    List<ServiceDescriptor> getKnownServices();

    /**
     * Lookup a remote service in the cache via some predicate
     */
    default Optional<ServiceDescriptor> findService( Predicate<ServiceDescriptor> predicate )
    {
        return getKnownServices().stream().filter(predicate).findFirst();
    }

    /**
     * Lookup a remote service in the cache via the muon:// url scheme
     */
    default Optional<ServiceDescriptor> getService( URI uri )
    {
        if( !uri.getScheme().equals( "muon" ) ){
            throw new IllegalArgumentException( "Discovery requires muon://XXX scheme urls for lookup" );
        }
        return findService( serviceDescriptor -> serviceDescriptor.getIdentifier().equals( uri.getHost() ) );
    }

    default String[] getCodecsForService( String hostName )
    {
        return findService( serviceDescriptor -> serviceDescriptor.getIdentifier().equals(hostName) ).map( ServiceDescriptor::getCodecs ).orElseGet( () -> new String[]{"application/json"} );
    }
}