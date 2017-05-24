package io.muoncore.javacpp;

import org.bytedeco.javacpp.annotation.Platform;
import org.bytedeco.javacpp.annotation.Properties;
import org.bytedeco.javacpp.tools.Info;
import org.bytedeco.javacpp.tools.InfoMap;
import org.bytedeco.javacpp.tools.InfoMapper;

/**
 * Created by adam on 01/05/17.
 */
@Properties(
    target = "io.muoncore.discovery.DiscoveryJni",
    value = {
        @Platform(
            include = {
                "io/muoncore/discovery/URI.h",
                "io/muoncore/discovery/ServiceDescriptor.h",
                "io/muoncore/discovery/DiscoveryOnReady.h",
                "io/muoncore/discovery/Discovery.h",
                "io/muoncore/discovery/ServiceDescriptorServer.h",
                "io/muoncore/discovery/ServiceDescriptorClient.h",
                "io/muoncore/discovery/MulticastDiscovery.h",
            },
            link = { "main@.1", "avrocpp@.1" }
        )
    }
)
public class DiscoveryJavaCppSpec implements InfoMapper
{
    public void map( InfoMap infoMap )
    {
        infoMap
            .put( new Info("std::vector<std::string>").pointerTypes("StringVector").define() )
            .put( new Info("std::vector<URI>").pointerTypes("URIVector").define() )
            .put( new Info("std::vector<ServiceDescriptor*>").pointerTypes("ServiceDescriptorPointerVector").define() )
            .put( new Info( "avro::codec_traits<ServiceDescriptorSer>" ).skip() )
        ;
    }
}