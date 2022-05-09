package Fragments

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.fragment.app.Fragment
import com.example.myapplication3.R
import com.google.android.gms.maps.*
import com.google.android.gms.maps.model.LatLng
import com.google.android.gms.maps.model.MarkerOptions


//class Fragment5 : Fragment() {
//
//    private lateinit var v: View
//    private var mMap: MapView? = null
//
//    override fun onCreateView(inflater: LayoutInflater, container: ViewGroup?, savedInstanceState: Bundle?): View? {
//        // Inflate the layout for this fragment
//        v = inflater.inflate(R.layout.fragment_5, container, false)
//        return v
//    }
//
//    override fun onStart() {
//        super.onStart()
//
//        //Snackbar.make(v, "Bienvenido: ", Snackbar.LENGTH_SHORT).show()
//    }
//
//}















class Fragment5 : Fragment(), OnMapReadyCallback {

    private var mMap: MapView? = null
    private lateinit var v: View

    override fun onSaveInstanceState(outState: Bundle) {
        super.onSaveInstanceState(outState)
        mMap?.onSaveInstanceState(outState)
    }

    override fun onCreateView(inflater: LayoutInflater, container: ViewGroup?, savedInstanceState: Bundle?): View {

        v = inflater.inflate(R.layout.fragment_5, container, false)

        mMap = v.findViewById(R.id.mapView) as MapView
        mMap?.onCreate(savedInstanceState)
        mMap?.getMapAsync(this)

        return v
    }

    override fun onResume() {
        super.onResume()
        mMap?.onResume()
    }

    override fun onPause() {
        super.onPause()
        mMap?.onPause()
    }

    override fun onStart() {
        super.onStart()
        mMap?.onStart()
    }

    override fun onStop() {
        super.onStop()
        mMap?.onStop()
    }

    override fun onDestroy() {
        super.onDestroy()
        mMap?.onDestroy()
    }

    override fun onLowMemory() {
        super.onLowMemory()
        mMap?.onLowMemory()
    }

    override fun onMapReady(googleMap: GoogleMap) {
        googleMap.addMarker(MarkerOptions().position(LatLng(0.0, 0.0)).title("Marker"))
    }
}
