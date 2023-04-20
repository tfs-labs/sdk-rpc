# about
    This is an SDK that sends transactions through other tfs nodes, implemented in C language.
    
The main work is to send a transaction request to the specified node (enable the RPC function) through http, and the node is responsible for composing the request into a transaction, and then sending it back to the SDK for signing, and then the node completes the transaction.
    
This SDK flow is for v0.22.x of the TFSC chain.
# Workflow

- Prepare the parameters required to request the transaction (via http request)

- Send the request to the TFS node, and the node returns the transaction body

- Sign the transaction, return to the node

Example: For more information, refer to JNI_JAVA/src/test/testMain.java