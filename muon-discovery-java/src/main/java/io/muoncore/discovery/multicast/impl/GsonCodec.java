package io.muoncore.discovery.multicast.impl;

import com.google.gson.Gson;

import java.io.UnsupportedEncodingException;
import java.lang.reflect.Type;
import java.nio.charset.StandardCharsets;

public class GsonCodec //implements MuonCodec
{
    private Gson gson = new Gson();

//    @Override
    public <T> T decode( byte[] encodedData, Type type )
    {
        return gson.fromJson( new String( encodedData, StandardCharsets.UTF_8 ), type );
    }

//    @Override
    public byte[] encode( Object data ) throws UnsupportedEncodingException
    {
        return gson.toJson(data).getBytes(StandardCharsets.UTF_8);
    }

//    @Override
    public String getContentType()
    {
        return "application/json";
    }
}