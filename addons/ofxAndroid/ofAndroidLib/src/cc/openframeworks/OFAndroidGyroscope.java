package cc.openframeworks;

import java.util.List;

import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.util.Log;

public class OFAndroidGyroscope extends OFAndroidObject {
	private SensorManager sensorManager;
    private Sensor gyroscope;
    
    private float timestamp;
    private static final float NS2S = 1.0f / 1000000000.0f;
    
    OFAndroidGyroscope(SensorManager sensorManager){
    	
        this.sensorManager = sensorManager;
        List<Sensor> sensors = sensorManager.getSensorList(Sensor.TYPE_GYROSCOPE);
        if(sensors.size() > 0)
        {
        	gyroscope = sensors.get(0);
        	sensorManager.registerListener(sensorListener, gyroscope, SensorManager.SENSOR_DELAY_GAME);   
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
		sensorManager.registerListener(sensorListener, gyroscope, SensorManager.SENSOR_DELAY_GAME);   
	}

	@Override
	protected void appStop() {
		sensorManager.unregisterListener(sensorListener);
	}
	
	
	private final SensorEventListener sensorListener = new SensorEventListener() {
		
		public void onSensorChanged(SensorEvent event) {

			float[] deltaRotationVector = new float[3];
			float EPSILON = (float) 0.0001;

			// This time step's delta rotation to be multiplied by the current rotation
			// after computing it from the gyro sample data.
			if (timestamp != 0) {
				final float dT = (event.timestamp - timestamp) * NS2S;
				// Axis of the rotation sample, not normalized yet.
				float axisX = event.values[0] * dT;
				float axisY = event.values[1] * dT;
				float axisZ = event.values[2] * dT;
				
				deltaRotationVector[0] = axisX;
				deltaRotationVector[1] = axisY;
				deltaRotationVector[2] = axisZ;

				updateGyroscope(deltaRotationVector[0], deltaRotationVector[1], deltaRotationVector[2]);
			}
			timestamp = event.timestamp;

		}
		 
		public void onAccuracyChanged(Sensor sensor, int accuracy) {}
	};

	public static native void updateGyroscope(float x, float y, float z);
    
}
