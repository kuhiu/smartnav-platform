package com.example.myapplication3

import android.content.Intent
import android.os.Bundle
import android.util.Log
import android.view.Menu
import android.view.MenuItem
import androidx.appcompat.app.AppCompatActivity
import androidx.navigation.fragment.NavHostFragment
import androidx.navigation.ui.NavigationUI
import androidx.preference.PreferenceManager
import com.google.android.material.bottomnavigation.BottomNavigationView


class MainActivity2 : AppCompatActivity() {

    private lateinit var bottomNavView : BottomNavigationView
    private lateinit var navHostFragment : NavHostFragment


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        val prefs = PreferenceManager.getDefaultSharedPreferences(this)

        if (prefs.getBoolean("drkmode",false) == true){
            setTheme(R.style.Dark_AppTheme)
            Log.d("Test","Tema oscuro seteado")
        }
        else{
            setTheme(R.style.AppTheme)
            Log.d("Test","Tema normal seteado")
        }

        setContentView(R.layout.activity_main2)

        navHostFragment = supportFragmentManager.findFragmentById(R.id.nav_host) as NavHostFragment
        bottomNavView = findViewById(R.id.bottom_bar)
        NavigationUI.setupWithNavController(bottomNavView, navHostFragment.navController)
    }

    override fun onCreateOptionsMenu(menu: Menu?): Boolean {            // Boton de settings comun a la main activity 2
        menuInflater.inflate(R.menu.settings_btn,menu)
        return super.onCreateOptionsMenu(menu)
    }


    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        val id = item.itemId

        if (id == R.id.btn_settings) {
            try {
                startActivity(Intent(this, SettingsActivity::class.java))
                return true
            } catch (e: Exception) {
                Log.d("Test","Error" + "\n")
            }
        }
        return super.onOptionsItemSelected(item)
    }

}

