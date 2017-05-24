package io.muoncore.javacpp;

import io.muoncore.discovery.DiscoveryJni.StringVector;

import java.util.Collection;
import java.util.Iterator;
import java.util.List;
import java.util.ListIterator;

/**
 * Created by adam on 17/05/17.
 */
public class JniStringList implements List<String>
{
    private final StringVector stringVector;

    public JniStringList( StringVector stringVector )
    {
        this.stringVector = stringVector;
    }

    @Override
    public int size()
    {
        return Long.valueOf( stringVector.size() ).intValue();
    }

    @Override
    public boolean isEmpty()
    {
        return stringVector.size() < 1;
    }

    @Override
    public boolean contains( Object o )
    {
        for( long i = stringVector.size() - 1; 0 <= i; i-- ){
            if( stringVector.get(i).getString().equals(o) ){
                return true;
            }
        }
        return false;
    }

    @Override
    public Iterator<String> iterator()
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
    public boolean add( String t )
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
    public boolean addAll( Collection<? extends String> c )
    {
        return false;
    }

    @Override
    public boolean addAll( int index, Collection<? extends String> c )
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
    public String get( int index )
    {
        return null;
    }

    @Override
    public String set( int index, String element )
    {
        return null;
    }

    @Override
    public void add( int index, String element )
    {

    }

    @Override
    public String remove( int index )
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
    public ListIterator<String> listIterator()
    {
        return null;
    }

    @Override
    public ListIterator<String> listIterator( int index )
    {
        return null;
    }

    @Override
    public List<String> subList( int fromIndex, int toIndex )
    {
        return null;
    }
}