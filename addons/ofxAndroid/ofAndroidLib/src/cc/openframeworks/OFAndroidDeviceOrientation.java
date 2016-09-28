package cc.openframeworks;

import java.util.List;

import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.util.Log;

public class OFAndroidDeviceOrientation extends OFAndroidObject {
	private SensorManager sensorManager;
    private Sensor orientation;
    
    private float timestamp;
    private static final float NS2S = 1.0f / 1000000000.0f;
    
    OFAndroidDeviceOrientation(SensorManager sensorManager){
        this.sensorManager = sensorManager;
        List<Sensor> sensors = sensorManager.getSensorList(Sensor.TYPE_ROTATION_VECTOR);
        if(sensors.size() > 0)
        {
        	orientation = sensors.get(0);
        	sensorManager.registerListener(sensorListener, orientation, SensorManager.SENSOR_DELAY_GAME);   
        	Log.v("OF", "gyroscope set up correctly");
        }else{
        	Log.e("OF","no gyroscope available");
        }
    }

	@Override
	protected void appPause() {
		sensorManager.unregisterListener(sensorListener);
		
	}

	@Override
	protected void appResume() {
		sensorManager.registerListener(sensorListener, orientation, SensorManager.SENSOR_DELAY_GAME);   
	}

	@Override
	protected void appStop() {
		sensorManager.unregisterListener(sensorListener);
	}
	
	
	private final SensorEventListener sensorListener = new SensorEventListener() {
		
		public void onSensorChanged(SensorEvent event) {
			
            updateDeviceOrientation(event.values[0], event.values[1], event.values[2], event.values[3]);
			
		}
		 
		public void onAccuracyChanged(Sensor sensor, int accuracy) {}
	};

	public static native void updateDeviceOrientation(float x, float y, float z, float w);
    
}
