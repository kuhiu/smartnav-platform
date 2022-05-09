package Fragments

import Entities.Usuarios
import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.EditText
import com.example.myapplication3.R
import com.google.android.material.snackbar.Snackbar
import database.UsuarioDao
import database.appDatabase
import java.lang.NullPointerException

class Fragment6 : Fragment() {

    private lateinit var v: View

    private lateinit var btn_chg : Button

    lateinit var edt_chgusr : EditText
    lateinit var edt_chgpwr : EditText
    lateinit var edt_chgpwr2 : EditText
    lateinit var edt_chgactualpwr : EditText

    private lateinit var user : Usuarios

    // Base de datos de usuarios
    private var db: appDatabase? = null
    private var userDao: UsuarioDao? = null

    override fun onCreateView(inflater: LayoutInflater, container: ViewGroup?, savedInstanceState: Bundle?): View {
        // Inflate the layout for this fragment
        v = inflater.inflate(R.layout.fragment_6, container, false)
        btn_chg = v.findViewById(R.id.btn_chg)
        edt_chgusr = v.findViewById(R.id.edt_chgusr)
        edt_chgpwr = v.findViewById(R.id.edt_chgpwr)
        edt_chgpwr2 = v.findViewById(R.id.edt_chgpwr2)
        edt_chgactualpwr = v.findViewById(R.id.edt_chgactualpwr)
        return v
    }

    override fun onStart() {
        super.onStart()

        db = appDatabase.getAppDataBase(v.context)
        userDao = db?.userDao()

        btn_chg.setOnClickListener {
            if ((edt_chgusr.length() > 0) && (edt_chgpwr.length() > 0) && (edt_chgpwr2.length() > 0)) {     // Chequeo si esta en la lista el usuario que ingreso y si esta vacio el campo
                if (edt_chgpwr.text.toString() == edt_chgpwr2.text.toString()) {
                    try {                                                                                   // Busco en la base de datos a ese usuario
                        user = userDao?.loadPersonByName(edt_chgusr.text.toString())!!
                        if (edt_chgactualpwr.text.toString() == user.password) {
                            userDao?.updatePerson(Usuarios(user.nombre, edt_chgpwr.text.toString()))
                            Snackbar.make(v, "Contraseña actualizada", Snackbar.LENGTH_SHORT).show()
                            activity?.onBackPressed()
                        }
                        else{
                            Snackbar.make(v, "Contraseña incorrecta", Snackbar.LENGTH_SHORT).show()
                        }

                    } catch (e: NullPointerException) {
                        Snackbar.make(v, "Usuario no registrado", Snackbar.LENGTH_SHORT).show()
                    }
                }
                else {   // las pw no coinciden
                    Snackbar.make(v, "Contraseñas no coinciden", Snackbar.LENGTH_SHORT).show()
                }
            }
        }
    }
}
