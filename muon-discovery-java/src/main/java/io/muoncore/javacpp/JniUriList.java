package io.muoncore.javacpp;

import io.muoncore.discovery.DiscoveryJni.URI;
import io.muoncore.discovery.DiscoveryJni.URIVector;

import java.util.Collection;
import java.util.Iterator;
import java.util.List;
import java.util.ListIterator;

/**
 * Created by adam on 17/05/17.
 */
public class JniUriList implements List<URI>
{
    private final URIVector uriVector;

    public JniUriList( URIVector stringVector )
    {
        this.uriVector = stringVector;
    }

    @Override
    public int size()
    {
        return Long.valueOf( uriVector.size() ).intValue();
    }

    @Override
    public boolean isEmpty()
    {
        return uriVector.size() < 1;
    }

    @Override
    public boolean contains( Object o )
    {
        return false;
    }

    @Override
    public Iterator<URI> iterator()
    {
        return null;
    }

    @Override
    public Object[] toArray()
    {
        return new Object[0];
    }

    @Override
    public <T1> T1[] toArray( T1[] a )
    {
        return null;
    }

    @Override
    public boolean add( URI t )
    {
        return false;
    }

    @Override
    public boolean remove( Object o )
    {
        return false;
    }

    @Override
    public boolean containsAll( Collection<?> c )
    {
        return false;
    }

    @Override
    public boolean addAll( Collection<? extends URI> c )
    {
        return false;
    }

    @Override
    public boolean addAll( int index, Collection<? extends URI> c )
    {
        return false;
    }

    @Override
    public boolean removeAll( Collection<?> c )
    {
        return false;
    }

    @Override
    public boolean retainAll( Collection<?> c )
    {
        return false;
    }

    @Override
    public void clear()
    {

    }

    @Override
    public URI get( int index )
    {
        return null;
    }

    @Override
    public URI set( int index, URI element )
    {
        return null;
    }

    @Override
    public void add( int index, URI element )
    {

    }

    @Override
    public URI remove( int index )
    {
        return null;
    }

    @Override
    public int indexOf( Object o )
    {
        return 0;
    }

    @Override
    public int lastIndexOf( Object o )
    {
        return 0;
    }

    @Override
    public ListIterator<URI> listIterator()
    {
        return null;
    }

    @Override
    public ListIterator<URI> listIterator( int index )
    {
        return null;
    }

    @Override
    public List<URI> subList( int fromIndex, int toIndex )
    {
        return null;
    }
}