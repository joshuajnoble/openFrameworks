package cc.openframeworks;

import java.util.List;

import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.util.Log;
import android.view.Display;
import android.view.Surface;
import android.view.WindowManager;

public class OFAndroidMagnetometer extends OFAndroidObject {
	private SensorManager sensorManager;
    private Sensor magnet;
    
    OFAndroidMagnetometer(SensorManager sensorManager){
        this.sensorManager = sensorManager;
        List<Sensor> sensors = sensorManager.getSensorList(Sensor.TYPE_MAGNETIC_FIELD);
        if(sensors.size() > 0)
        {
        	magnet = sensors.get(0);
        	sensorManager.registerListener(sensorListener, magnet, SensorManager.SENSOR_DELAY_GAME);   
        	Log.v("OF", "magnetometer set up correctly");
        }else{
        	Log.e("OF","no magnetometer available");
        }
    }

	@Override
	protected void appPause() {
		sensorManager.unregisterListener(sensorListener);
		
	}

	@Override
	protected void appResume() {
		sensorManager.registerListener(sensorListener, magnet, SensorManager.SENSOR_DELAY_GAME);   
	}

	@Override
	protected void appStop() {
		sensorManager.unregisterListener(sensorListener);
	}
	
	
	private final SensorEventListener sensorListener = new SensorEventListener() {
		public void onSensorChanged(SensorEvent event) {
	    	WindowManager windowManager = (WindowManager)OFAndroid.getContext().getSystemService(Context.WINDOW_SERVICE);
	    	Display display = windowManager.getDefaultDisplay();
	    	
			updateMagnetometer(event.values[0], event.values[1], event.values[2]);
		}
		 
		public void onAccuracyChanged(Sensor sensor, int accuracy) {}
	};

	public static native void updateMagnetometer(float x, float y, float z);
    
}
