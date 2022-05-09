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


class Fragment3 : Fragment() {

    lateinit var v: View
    private lateinit var btn_reg : Button
    private lateinit var edt_reguser : EditText
    private lateinit var edt_regpw : EditText

    // Base de datos de usuarios
    private var db: appDatabase? = null
    private var userDao: UsuarioDao? = null

    override fun onCreateView(inflater: LayoutInflater, container: ViewGroup?, savedInstanceState: Bundle?): View {
        // Inflate the layout for this fragment
        v = inflater.inflate(R.layout.fragment_fragment3, container, false)
        btn_reg = v.findViewById(R.id.btn_chg)
        edt_reguser = v.findViewById(R.id.edt_chgusr)
        edt_regpw = v.findViewById(R.id.edt_chgpwr)
        return v
    }


    override fun onStart() {
        super.onStart()

        db = appDatabase.getAppDataBase(v.context)
        userDao = db?.userDao()

        btn_reg.setOnClickListener {                            // Boton Registrese
            val onConflict = userDao?.insertPerson( Usuarios(edt_reguser.text.toString(),edt_regpw.text.toString()) )     // Inserto usuario en la base de datos
            //Log.d("Test",OnConflict.toString() + "\n")

            if (onConflict == (-1).toLong() )                   // Si insertPerson devuelve -1 significa que el usuario ya existe
                Snackbar.make(v, "El usuario ya existe", Snackbar.LENGTH_SHORT).show()
            else{
                Snackbar.make(v, "Usuario agregado con exito", Snackbar.LENGTH_SHORT).show()
                activity?.onBackPressed()                       // El usuario fue agregado, vuelvo a la pantalla de inicio
            }
        }
    }

}
