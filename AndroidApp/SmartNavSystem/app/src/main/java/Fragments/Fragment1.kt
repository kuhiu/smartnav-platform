package Fragments

import Entities.Usuarios
import android.content.Context
import android.content.Intent
import android.content.Intent.FLAG_ACTIVITY_CLEAR_TOP
import android.content.SharedPreferences
import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.CheckBox
import android.widget.EditText
import android.widget.TextView
import androidx.navigation.findNavController
import com.example.myapplication3.MainActivity2
import com.example.myapplication3.R
import com.google.android.material.snackbar.Snackbar
import database.UsuarioDao
import database.appDatabase
import java.lang.NullPointerException


class Fragment1 : Fragment() {

    lateinit var v : View

    private lateinit var btn_newuser : Button
    private lateinit var btn_init    : Button
    private lateinit var btn_eraseuser : Button

    private lateinit var  edt_user : EditText
    private lateinit var  edt_pw   : EditText

    private lateinit var txt_olvidepw : TextView

    private lateinit var user : Usuarios

    private lateinit var checkBox : CheckBox

    private lateinit var intent : Intent

    // Base de datos de usuarios
    private var db: appDatabase? = null
    private var userDao: UsuarioDao? = null

    override fun onCreateView(inflater: LayoutInflater, container: ViewGroup?, savedInstanceState: Bundle?): View {
        v = inflater.inflate(R.layout.fragment_fragment1, container, false)
        btn_init = v.findViewById(R.id.btn_init)
        btn_newuser = v.findViewById(R.id.btn_newuser)
        edt_user = v.findViewById(R.id.edt_user)
        edt_pw = v.findViewById(R.id.edt_pw)
        checkBox = v.findViewById(R.id.checkBox)
        txt_olvidepw = v.findViewById(R.id.txt_olvidepw)
        btn_eraseuser = v.findViewById(R.id.btn_eraseuser)
        return v
    }

    override fun onStart() {
        super.onStart()

        val sharedPref: SharedPreferences = requireContext().getSharedPreferences(getString(R.string.shr_preference), Context.MODE_PRIVATE)
        val editor = sharedPref.edit()

        db = appDatabase.getAppDataBase(v.context)
        userDao = db?.userDao()

        if ( sharedPref.getBoolean("Check", false ) ) {                         // Si el usuario quizo guardar su usuario (utilizacion de share preference)
            if ( !(sharedPref.getString("USER", "default").equals("") && sharedPref.getString("PW", "default").equals("")) ) {
                edt_user.setText(sharedPref.getString("USER", "default"))       // Escribo los edit text de usuario y contraseña
                edt_pw.setText(sharedPref.getString("PW", "default"))           // para que no tenga que volver a escribirlos
            }
        }

        checkBox.isChecked = sharedPref.getBoolean("Check", false )             // Ademas guardo el estado del tick para el proximo inicio de sesion

        btn_init.setOnClickListener{                                            // Boton inicio de sesion
            if ( (edt_user.length()>0) && (edt_pw.length()>0) ) {               // Chequeo si esta en la lista el usuario que ingreso y si esta vacio el campo
                    try {                                                       // Busco en la base de datos a ese usuario
                        user = userDao?.loadPersonByName(edt_user.text.toString())!!
                        // En caso de haber encontrado el usuario y user no sea NULL (no salta por excepción)
                        // verifico que coincida usuario y contraseña
                        if ( (edt_user.text.toString() == user.nombre) && (edt_pw.text.toString() == user.password) ) {
                            if (checkBox.isChecked) {                           // Guardo si checkbox en la sharepreference usuario y contraseña
                                editor.putString("USER", edt_user.text.toString())
                                editor.putString("PW", edt_pw.text.toString())
                                editor.putBoolean("Check", checkBox.isChecked)
                                editor.apply()
                            }
                            else {                                              // Si el checkbox no fue tildada dejo vacio la sharepreference
                                editor.putString("USER", "")                    // para que cuando vuelva a iniciar no cargue los datos en los edittext
                                editor.putString("PW", "")
                                editor.putBoolean("Check", checkBox.isChecked)
                                editor.apply()
                            }
                            // Log.d("Test",sharedPref.getString("USER","default") + sharedPref.getString("PW","default")!! + "\n")
                            // Siguiente pantalla
                            //val action = Fragment1Directions.actionFragment1ToMainActivity2()       // Consultar
                            //v.findNavController().navigate(action)
                            intent = Intent(context, MainActivity2::class.java)
                            intent.flags = FLAG_ACTIVITY_CLEAR_TOP
                            startActivity(intent)
                            activity?.finish()
                        }
                        else {
                            Snackbar.make(v, "Contraseña incorrecta", Snackbar.LENGTH_SHORT).show()
                        }
                    }
                    catch (e : NullPointerException){
                        Snackbar.make(v, "Usuario no registrado", Snackbar.LENGTH_SHORT).show()
                    }
            }
            else
                Snackbar.make(v, "Campo de datos vacio", Snackbar.LENGTH_SHORT).show()
        }

        btn_newuser.setOnClickListener{                                         // Boton crear usuario
            val action2 = Fragment1Directions.actionFragment1ToFragment3()
            v.findNavController().navigate(action2)
        }

        btn_eraseuser.setOnClickListener {                                      // Boton borrar usuario

            if ( (edt_user.length()>0) && (edt_pw.length()>0) ) {               // Chequeo si esta en la lista el usuario que ingreso y si esta vacio el campo
                try {                                                           // Busco en la base de datos a ese usuario
                    user = userDao?.loadPersonByName(edt_user.text.toString())!!
                    // En caso de haber encontrado el usuario y user no sea NULL (no salta por excepción)
                    // verifico que coincida usuario y contraseña
                    if ( (edt_user.text.toString() == user.nombre) && (edt_pw.text.toString() == user.password) ) {
                        userDao?.deletePerson(Usuarios(edt_user.text.toString(), edt_pw.text.toString()))           // Elimino usuario
                        Snackbar.make(v, "Usuario eliminado", Snackbar.LENGTH_SHORT).show()
                    }
                    else
                        Snackbar.make(v, "Contraseña incorrecta", Snackbar.LENGTH_SHORT).show()
                }
                catch (e : NullPointerException){
                    Snackbar.make(v, "Usuario no registrado", Snackbar.LENGTH_SHORT).show()
                }
            }
            else
                Snackbar.make(v, "Campo de datos vacio", Snackbar.LENGTH_SHORT).show()
        }

        txt_olvidepw.setOnClickListener{                                        // Texto clickeable azul "Olvide mi contraseña"
            val action = Fragment1Directions.actionFragment1ToFragment6()
            v.findNavController().navigate(action)
        }

    }
}

