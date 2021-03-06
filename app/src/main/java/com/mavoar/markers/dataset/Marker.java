package com.mavoar.markers.dataset;

import java.io.Serializable;
import java.util.ArrayList;

/**
 * Created by al on 05-03-2017.
 */

public class Marker implements Serializable{
    private String name;
    private ArrayList<Float> rotation;
    private ArrayList<Float> translation;

    public Marker(String name, ArrayList<Float> rotation, ArrayList<Float> translation) {
        this.name = name;
        this.rotation = rotation;
        this.translation = translation;
    }


    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public ArrayList<Float> getRotation() {
        return rotation;
    }

    public void setRotation(ArrayList<Float> rotation) {
        this.rotation = rotation;
    }

    public ArrayList<Float> getTranslation() {
        return translation;
    }

    public void setTranslation(ArrayList<Float> translation) {
        this.translation = translation;
    }

    public void reverseTransformations(){
        ArrayList<Float> reverseRot= new ArrayList<>();
        ArrayList<Float> reverseTra= new ArrayList<>();

        for(Float r:this.rotation){
            reverseRot.add(r);
        }
        for(Float t: this.translation){
            reverseTra.add(-t);
        }

        this.rotation= reverseRot;
        this.translation= reverseTra;
    }

}
