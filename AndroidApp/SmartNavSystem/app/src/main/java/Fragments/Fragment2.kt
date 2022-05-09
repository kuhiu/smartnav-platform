package Fragments

import android.os.Bundle
import android.util.Log
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.MenuItem
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import androidx.preference.PreferenceManager
import com.example.myapplication3.R
import com.google.android.material.snackbar.Snackbar


class Fragment2 : Fragment() {

    lateinit var v: View

    override fun onCreateView(inflater: LayoutInflater, container: ViewGroup?, savedInstanceState: Bundle?): View? {
        // Inflate the layout for this fragment
        v = inflater.inflate(R.layout.fragment_2, container, false)
        return v
    }

    override fun onStart() {
        super.onStart()
        //Snackbar.make(v, "Bienvenido: ", Snackbar.LENGTH_SHORT).show()
    }

}


