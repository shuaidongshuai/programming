package com.dong.stream;

import org.junit.Test;

import java.util.Arrays;
import java.util.List;
import java.util.stream.Stream;

import static java.util.stream.Collectors.toList;
import static org.junit.Assert.assertEquals;

public class FlatMap {
    @Test
    public void test1(){
        List<Integer> together = Stream.of(Arrays.asList(1, 2), Arrays.asList(3, 4))
                .flatMap(numbers -> numbers.stream())
                .collect(toList());
        assertEquals(Arrays.asList(1, 2, 3, 4), together);
    }

    @Test
    public void test3(){
        List<Integer> together = Stream.of(Arrays.asList(1, 2), Arrays.asList(3, 4))
                .flatMap(numbers -> numbers.stream())
                .map(number -> number * number)
                .collect(toList());
        for (Integer i : together){
            System.out.println(i);
        }
    }

    @Test
    public void test2(){
        Artist artist1 = new Artist("dong1", "中国1");
        Artist artist2 = new Artist("dong2", "中国2");
        Artist artist3 = new Artist("dong3", "中国3");

        List<String> namesAndOrigins = getNamesAndOrigins(Arrays.asList(artist1, artist2, artist3));
        for(String s : namesAndOrigins){
            System.out.println(s);
        }
    }

    public static List<String> getNamesAndOrigins(List<Artist> artists) {
        return artists.stream()
                .flatMap(artist -> Stream.of(artist.getName(), artist.getNationality()))
                .collect(toList());
    }
}
