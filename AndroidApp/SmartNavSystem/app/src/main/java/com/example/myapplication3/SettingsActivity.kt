package com.example.myapplication3

import android.content.Intent
import android.os.Bundle
import android.util.Log
import androidx.appcompat.app.AppCompatActivity
import androidx.preference.PreferenceFragmentCompat
import androidx.preference.PreferenceManager



class SettingsActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        val prefs = PreferenceManager.getDefaultSharedPreferences(this)

        if (prefs.getBoolean("drkmode",false)){
            setTheme(R.style.Dark_AppTheme)
            Log.d("Test","Tema oscuro seteado")
        }
        else{
            setTheme(R.style.AppTheme)
            Log.d("Test","Tema normal seteado")
        }

        setContentView(R.layout.settings_activity)
        supportFragmentManager
            .beginTransaction()
            .replace(R.id.settings, SettingsFragment())
            .commit()
        supportActionBar?.setDisplayHomeAsUpEnabled(true)
    }

    class SettingsFragment : PreferenceFragmentCompat() {
        override fun onCreatePreferences(savedInstanceState: Bundle?, rootKey: String?) {
            setPreferencesFromResource(R.xml.root_preferences, rootKey)
        }
    }

    override fun onBackPressed() {
        //finish()
        try {
            startActivity(Intent(this, MainActivity2::class.java))
        } catch (e: Exception) {
            Log.d("Test","Error" + "\n")
        }
    }



}