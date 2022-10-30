package com.example.myapplication3

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import androidx.preference.PreferenceManager


class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        val prefs = PreferenceManager.getDefaultSharedPreferences(this)
        if (prefs.getBoolean("drkmode",false) == true){         // Utilizacion de share preference
            setTheme(R.style.Dark_AppTheme)
            Log.d("Test","Tema oscuro seteado")
        }
        else{
            setTheme(R.style.AppTheme)
            Log.d("Test","Tema normal seteado")
        }
        setContentView(R.layout.activity_main)
    }


}
